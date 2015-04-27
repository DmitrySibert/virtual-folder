using HWdTech.DS.v30;
using HWdTech.DS.v30.Messages;
using HWdTech.DS.v30.PropertyObjects;
using System.Collections.Generic;

namespace VirtualFolderAdapter.Messages
{
    class DropFilesMessage
    {
        public static bool IsMeet(IMessage message)
        {
            return Folder.IsSet(message) && Files.IsSet(message);
        }
        public static Field<string> Folder
        {
            get
            {
                return folder;
            }
        }
        public static Field<List<string>> Files
        {
            get
            {
                return files;
            }
        }

        static Field<string> folder = new Field<string>("Folder");
        static Field<List<string>> files = new Field<List<string>>("Files");
    }
}
