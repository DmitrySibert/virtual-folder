using HWdTech.DS.v30;
using HWdTech.DS.v30.Messages;
using HWdTech.DS.v30.PropertyObjects;

namespace VirtualFolderAdapter.Messages
{
    class OpenFileMessage
    {
        public static bool IsMeet(IMessage message)
        {
            return FileName.IsSet(message) && CurrentPath.IsSet(message);
        }
        public static Field<string> FileName
        {
            get
            {
                return fileName;
            }
        }
        public static Field<string> CurrentPath
        {
            get
            {
                return currentPath;
            }
        }
        static Field<string> fileName = new Field<string>("FileName");
        static Field<string> currentPath = new Field<string>("CurrentPath");
    }
}
