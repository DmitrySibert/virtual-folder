using HWdTech.DS.v30;
using HWdTech.DS.v30.Messages;
using HWdTech.DS.v30.PropertyObjects;

namespace VirtualFolderAdapter.Messages
{
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
}
