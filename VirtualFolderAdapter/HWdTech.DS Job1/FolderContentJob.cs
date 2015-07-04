using System;
using System.Collections.Generic;
using System.Diagnostics;
using HWdTech;
using HWdTech.DS.v30;
using HWdTech.DS.v30.Channels;
using HWdTech.DS.v30.Messages;
using HWdTech.DS.v30.PropertyObjects;
using HWdTech.Factories;
using VirtualFolderAdapter.Messages;

[assembly: DIObjectCreationRule("FolderContentJob", typeof(DataAdapter.FolderContent.FolderContentJob))]

namespace DataAdapter.FolderContent
{
    struct FolderItem
    {
        public Boolean isFolder;
        public String title;
        public FolderItem(Boolean isFolder, String title)
        {
            this.isFolder = isFolder;
            this.title = title;
        }
    };

    [NeedChannel("FolderContent", IsTyped = true)]
    public class FolderContentJob : IJob
    {

        public FolderContentJob(IObject message)
        {
            Console.WriteLine("Instance of EchoJos has been created." + message);
        }

        [ChannelEndpointHanlder("FolderContent", MessageType = "Path")]
        public void GiveFolderContent(IMessage message)
        {
            if (FolderContentMessage.IsMeet(message))
            {
                Console.WriteLine("Path to load = {0}", FolderContentMessage.Path[message]);
                Field<List<FolderItem>> pathContent = new Field<List<FolderItem>>("FolderContent");
                MessageBus.TrySendSuccessResponse(message, (m) =>
                {
                    List<FolderItem> items = new List<FolderItem>();
                    FolderItem folderItem = new FolderItem(true, "Documents");
                    items.Add(folderItem);
                    folderItem = new FolderItem(false, "waybill.xls");
                    items.Add(folderItem);
                    folderItem = new FolderItem(false, "Report.doc");
                    items.Add(folderItem);
                    folderItem = new FolderItem(true, "Reports");
                    items.Add(folderItem);
                    pathContent[m] = items;
                });

                ObjectBuilder builder = Singleton<DIFactory>.Instance.Create<ObjectBuilder>();
                IMessage message1 = Singleton<DIFactory>.Instance.Create<IMessage>();
                builder.Message().Type("CurrentFolder").To(Singleton<DIFactory>.Instance.Create<IChannel>("Cookie")).Make(message1);
                FolderContentMessage.Path[message1] = FolderContentMessage.Path[message];
                MessageBus.Send(message1);
            }
        }

        [ChannelEndpointHanlder("FolderContent", MessageType = "DropFiles")]
        public void dropFiles(IMessage message)
        {
            if (DropFilesMessage.IsMeet(message))
            {
                Console.WriteLine("Folder to drop = {0}", DropFilesMessage.Folder[message]);
                foreach(String file in DropFilesMessage.Files[message])
                {
                    Console.WriteLine("File dropped = {0}", file);
                }
                MessageBus.TrySendUnsuccessResponse(message, "Files dropping success");
            }
        }

        [ChannelEndpointHanlder("FolderContent", MessageType = "TryOpenFile")]
        public void tryOpenFile(IMessage message)
        {
            if(TryOpenFileMessage.IsMeet(message))
            {
                ObjectBuilder builder = Singleton<DIFactory>.Instance.Create<ObjectBuilder>();
                IMessage message1 = Singleton<DIFactory>.Instance.Create<IMessage>();
                builder.Message().To(Singleton<DIFactory>.Instance.Create<IChannel>("Cookie")).Make(message1);
                CookieRequestMessage.Type[message1] = "Parameters";
                CookieRequestMessage.FileName[message1] = TryOpenFileMessage.FileName[message];
                MessageBus.Send(message1);
            }
        }

        [ChannelEndpointHanlder("FolderContent", MessageType = "OpenFile")]
        public void runFile(IMessage message)
        {
            if (OpenFileMessage.IsMeet(message))
            {
                String path = OpenFileMessage.CurrentPath[message] + "\\" + OpenFileMessage.FileName[message];
                Process.Start(@path);
            }
        }
    }
}
