﻿/*
* AIUIAgentClient.h
*
*  Created on: 2017年3月9日
*      Author: hj
*/

#ifndef AIUIAGENTCLIENT_H_
#define AIUIAGENTCLIENT_H_

#include <aiui/AIUI.h>


#include <string>
#include <iostream>

#include "FileUtil.h"
#include "Log.h"

#ifdef _MSC_VER
#include <windows.h>
#include <process.h>
#define CLIENT_ROOT_DIR ".\\AIUI"
#define CFG_FILE_PATH CLIENT_ROOT_DIR##"\\cfg\\aiui.cfg"
#define CLIENT_AUDIO_PATH CLIENT_ROOT_DIR##"\\audio\\test.pcm"
#define LOG_DIR CLIENT_ROOT_DIR##"\\log"
#else
#include <unistd.h>
#define CLIENT_ROOT_DIR "/home/anxingg/AIUI"
#define CFG_FILE_PATH CLIENT_ROOT_DIR##"/cfg/aiui.cfg"
#define CLIENT_AUDIO_PATH CLIENT_ROOT_DIR##"/test/audio/test.pcm"
#define LOG_DIR CLIENT_ROOT_DIR##"/log"
#endif

#define LOG_NAME_AIUI_CLIENT "AIUIClient"
//等待AIUI响应的时间间隔
#define AIUI_EVENT_WAIT_TIMEOUT 30000
using namespace aiui;
using namespace std;


class WriteAudioThread 
{
private:
	IAIUIAgent* mAgent;

	string mAudioPath;

	bool mRepeat;

	bool mRun;

	FileUtil::DataFileHelper* mFileHelper;

	HANDLE  thread_hdl_;
	unsigned int  thread_id_;


private:
	bool threadLoop();

	static unsigned int __stdcall WriteProc(void * paramptr) ;


public:
	WriteAudioThread(IAIUIAgent* agent, const string& audioPath, bool repeat);

	~WriteAudioThread();

	void stopRun();

	bool run();

};


class AIUIClient: public IAIUIListener
{
public:
	int mnState;
private:
	IAIUIAgent* agent;

	WriteAudioThread * writeThread;
	//日志类
	Log m_WriteLog;
public:
	AIUIClient() ;

	~AIUIClient();
public:
	void createAgent();
	void wakeup();
	void start();
	void stop();
	void write(bool repeat);
	void stopWriteThread();
	void reset();
	void writeText();
	void sync();
	void destory();
private:
	void onEvent(IAIUIEvent& event);
public:
	void readCmd();
	void test();
};

#endif /* AIUIAGENTCLIENT_H_ */
