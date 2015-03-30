using HWdTech.DS.v30;
using HWdTech.DS.v30.Messages;
using HWdTech.DS.v30.PropertyObjects;

namespace VirtualFolderAdapter.Messages
{
    class TryOpenFileMessage
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
}
