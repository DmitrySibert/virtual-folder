using System;
using System.Collections.Generic;
using HWdTech;
using HWdTech.DS.v30;
using HWdTech.DS.v30.Channels;
using HWdTech.DS.v30.Messages;
using HWdTech.DS.v30.PropertyObjects;
using HWdTech.Factories;

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

    class FolderContentMessage
    {
        public static bool IsMeet(IMessage message)
        {
            return Path.IsSet(message);
        }

        public static Field<string> Path
        {
            get
            {
                return path;
            }
        }

        static Field<string> path = new Field<string>("Path");
    }

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
            }
        }
    }
}
