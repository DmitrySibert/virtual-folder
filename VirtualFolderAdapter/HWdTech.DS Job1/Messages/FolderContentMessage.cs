using HWdTech.DS.v30;
using HWdTech.DS.v30.Messages;
using HWdTech.DS.v30.PropertyObjects;

namespace VirtualFolderAdapter.Messages
{
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
}
