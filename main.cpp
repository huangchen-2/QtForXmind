#include "mainwidget.h"

#include <QApplication>
#include <QDateTime>
#include "Windows.h"
#include "DbgHelp.h"
#pragma comment(lib, "dbghelp.lib")

int GenerateMiniDump(PEXCEPTION_POINTERS pExceptionPointers)
{
    QString dmpFileName = QString("%1.dmp").arg(QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss"));
    QString dmpFile = QString("%1/%2").arg(QApplication::applicationDirPath()).arg(dmpFileName);

    //将QString 转为 const char*
    HANDLE hDumpFile = CreateFileW(dmpFile .toStdWString().c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, 0, CREATE_ALWAYS, 0, 0);
    if (hDumpFile != INVALID_HANDLE_VALUE)
    {
        MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
        dumpInfo.ThreadId = GetCurrentThreadId();
        dumpInfo.ExceptionPointers = pExceptionPointers;
        dumpInfo.ClientPointers = TRUE;

        // 创建Dump文件
        MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpWithDataSegs, pExceptionPointers ? &dumpInfo : nullptr, nullptr, nullptr);
        CloseHandle(hDumpFile);
    }

    return EXCEPTION_EXECUTE_HANDLER;
}

LONG WINAPI ExceptionFilter(LPEXCEPTION_POINTERS lpExceptionInfo)
{
    // 这里做一些异常的过滤或提示
    if (IsDebuggerPresent())
    {
        return EXCEPTION_CONTINUE_SEARCH;
    }
    return GenerateMiniDump(lpExceptionInfo);
}



int main(int argc, char *argv[])
{
    SetUnhandledExceptionFilter(ExceptionFilter);
    QApplication a(argc, argv);
    MainWidget w;
    w.show();
    return a.exec();
}
