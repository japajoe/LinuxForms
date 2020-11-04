#ifndef DIALOGRESULT_HPP
#define DIALOGRESULT_HPP

namespace LinuxForms
{
    enum class DialogResult
    {
        Abort = 3,  //The dialog box return value is Abort (usually sent from a button labeled Abort).
        Cancel = 2, //The dialog box return value is Cancel (usually sent from a button labeled Cancel).
        Ignore = 5, //The dialog box return value is Ignore (usually sent from a button labeled Ignore).
        No = 7,     //The dialog box return value is No (usually sent from a button labeled No).
        None = 0,   //Nothing is returned from the dialog box. This means that the modal dialog continues running.
        OK = 1,     //The dialog box return value is OK (usually sent from a button labeled OK).
        Retry =	4,  //The dialog box return value is Retry (usually sent from a button labeled Retry).
        Yes = 6     //The dialog box return value is Yes (usually sent from a button labeled Yes).
    };
}
#endif