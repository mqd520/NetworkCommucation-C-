#include "stdafx.h"
#include "TestThread.h"

CTestThread::CTestThread()
{

}

CTestThread::~CTestThread()
{

}

void CTestThread::OnThreadExecute()
{

}

void CTestThread::OnThreadCmp()
{
	OutputDebugString(_T("OnThreadCmp \n"));
}