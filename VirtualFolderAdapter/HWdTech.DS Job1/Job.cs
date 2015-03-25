using System;

using HWdTech;
using HWdTech.DS.v30;
using HWdTech.DS.v30.Channels;
using HWdTech.DS.v30.Messages;
using HWdTech.DS.v30.PropertyObjects;
using HWdTech.Factories;
using System.Collections.Generic;

//{IsRequest:true,ID:'2',To:{Name:'FileStorage'},  Type: "UploadFile", "First": "lkdfgnlfdkngdlkgnfgdnfg"}

//[assembly: DIObjectCreationRule("MyJob", typeof(HWdTech.DS_Job1.Job))]
[assembly: DIObjectCreationRule("Logger", typeof(HWdTech.DS_Job1.LogJob))]

namespace HWdTech.DS_Job1
{
    class StartMessage
    {
        public static bool IsMeet(IMessage message)
        {
            return FileName.IsSet(message);
        }

        public static Field<string> FileName
        {
            get
            {
                return fileName;
            }
        }

        static Field<string> fileName = new Field<string>("FileName");
    }

    class LogMessage
    {
        public static bool IsMeet(IMessage message)
        {
            return LogMsg.IsSet(message);
        }

        public static Field<string> LogMsg
        {
            get
            {
                return logMsg;
            }
        }

        static Field<string> logMsg = new Field<string>("LogMsg");
    }

    [Option("myName", "Value")]
    [NeedChannel("channel1", IsTyped = true)]
    [NeedChannel("UploadFile", IsTyped = true)]
    public class Job : IJob
    {

        public Job(IObject message)
        {
            Console.WriteLine("Instance of EchoJos has been created." + message);
        }

        [ChannelEndpointHanlder("UploadFile", MessageType ="Start")]
        public void UploadFileHandler(IMessage message)
        {
            if (StartMessage.IsMeet(message))
            {
                Console.WriteLine("Start new upload message has been got");
                Console.WriteLine("File to Load = {0}", StartMessage.FileName[message]);
                Field<int> something = new Field<int>("something");
                Console.WriteLine("something = {0}", something[message]);
                Field<string> uniqueId = new Field<string>("UniqueID");
                MessageBus.TrySendSuccessResponse(message, (m) => { uniqueId[m] = Guid.NewGuid().ToString(); });
            }
            else
            {
                MessageBus.TrySendUnsuccessResponse(message, "Wrong format of the message");
            }
        }

        public void DowloadFileHandler(IMessage message)
        {
            Console.WriteLine("CHANNEL 1 type 2");
            MessageBus.TrySendSuccessResponse(message);
        }
    }

    [Option("myName", "Value")]
    [NeedChannel("channel1", IsTyped = true)]
    [NeedChannel("Logger", IsTyped = true)]
    public class LogJob : IJob
    {
        public LogJob(IObject message)
        {
            Console.WriteLine("Instance of Logger has been created." + message);
        }

        [ChannelEndpointHanlder("Logger", MessageType = "Log")]
        public void UploadFileHandler(IMessage message)
        {
            if (LogMessage.IsMeet(message))
            {
                Console.WriteLine("Log message = {0}", LogMessage.LogMsg[message]);
                Field<string> uniqueId = new Field<string>("UniqueID");
                MessageBus.TrySendSuccessResponse(message, (m) => { uniqueId[m] = Guid.NewGuid().ToString(); });
            }
            else
            {
                MessageBus.TrySendUnsuccessResponse(message, "Wrong format of the message");
            }
        }
    }
}