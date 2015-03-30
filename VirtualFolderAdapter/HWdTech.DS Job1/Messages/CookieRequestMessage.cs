using HWdTech.DS.v30;
using HWdTech.DS.v30.Messages;
using HWdTech.DS.v30.PropertyObjects;

namespace VirtualFolderAdapter.Messages
{
    class CookieRequestMessage
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
        static public Field<string> Type
        {
            get
            {
                return type;
            }
        }
        static Field<string> fileName = new Field<string>("FileName");
        static Field<string> type = new Field<string>("Type", Field<string>.NotNull);
    }
}
