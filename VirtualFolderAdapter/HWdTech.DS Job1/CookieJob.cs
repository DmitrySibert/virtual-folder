using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using HWdTech;
using HWdTech.DS.v30;
using HWdTech.DS.v30.Channels;
using HWdTech.DS.v30.Messages;
using HWdTech.DS.v30.PropertyObjects;
using HWdTech.Factories;
using VirtualFolderAdapter.Messages;

[assembly: DIObjectCreationRule("CookieJob", typeof(VirtualFolderAdapter.CookieJob))]

namespace VirtualFolderAdapter
{
    [NeedChannel("Cookie", IsTyped = true)]
    class CookieJob : IJob
    {
        private String folder = "D:/";

        public CookieJob(IObject message)
        {
            Console.WriteLine("Instance of CookieJob has been created." + message);
        }

        [ChannelEndpointHanlder("Cookie", MessageType = "Parameters")]
        public void sendRequestedParameter(IMessage message)
        {
            ObjectBuilder builder = Singleton<DIFactory>.Instance.Create<ObjectBuilder>();
            IMessage message1 = Singleton<DIFactory>.Instance.Create<IMessage>();
            builder.Message().To(Singleton<DIFactory>.Instance.Create<IChannel>("FolderContent")).Make(message1);
            OpenFileMessage.CurrentPath[message1] = this.folder;
            OpenFileMessage.FileName[message1] = TryOpenFileMessage.FileName[message];
            Field<String> type = new Field<String>("Type");
            type[message1] = "OpenFile";
            MessageBus.Send(message1);
        }
    }
}
