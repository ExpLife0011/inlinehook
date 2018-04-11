#pragma once

#ifdef __cplusplus
extern "C" {
#endif


#ifdef _KERNEL_HOOK
#include <minwindef.h>
#else
#include <windows.h>
#endif

#define  BACKUPCODE_SIZE  0x200
	/*
	1. hook����ִ�е�ʱ�򣬸����Ĵ����Ļ���������ͨ��ֱ���޸���Щֵ�ԼĴ���������
	2. ���Ը���esp�Բ������й���
	*/
	typedef struct _HookContex
	{
		ULONG uEflags;
		ULONG uEdi;
		ULONG uEsi;
		ULONG uEbp;
		ULONG uEsp;
		ULONG uEbx;
		ULONG uEdx;
		ULONG uEcx;
		ULONG uEax;
	}HookContex;

	//hook������ָ��������
	typedef void(_stdcall *fpTypeHookFun)(HookContex* hookContex);
	//inlinehook�Ľṹ�壬���ù�ע��Щϸ�ڣ�ֱ��ʹ�ó�ʼ�������Զ�����������,���Բ��ù�ע����ṹ��
	typedef  struct  _InlineHookSt
	{
		PVOID lpHookAddr;   //��hook�ĵ�ַ
		int nOpcodeMove; //��lpHookAddr�㿪ʼ���㣬��Ҫ�ƶ�����ָ�movedOpCode
		BYTE backupCode[BACKUPCODE_SIZE];  //��hook�ָ���ʱ��,������ԭ��ָ��
		//
		BYTE*  hookEntry;   //hook���
		BYTE* movedOpCode; //�ƶ���opcode�Ļ�����
		fpTypeHookFun lpNewProc;  //���ǵĺ�����ַ
		BOOL bHookSucc; //hook�Ƿ�ɹ�
	}InlineHookSt;


	/*
	����˵����
	    inlineSt�� inline hook�Ľṹ��,ֱ�Ӵ���һ���ṹ���ָ�뼴�ɣ�������ʼ����������������
	    lpHookAddr�� �������ַ��ʼ�ĵط�
	    lpNewProc�� �µĺ�����ַ
	*/
	BOOL InitInlineHook(OUT InlineHookSt* inlineSt, IN PVOID lpHookAddr, IN fpTypeHookFun lpNewProc);


	/*
	����˵����
	    inlineSt�� ֱ�Ӵ���InitInlineHook��ʼ����inlineSt����
	*/
	BOOL InstallInlineHook(IN InlineHookSt* inlineSt);


	/*
	����˵����
	    inlineSt�� ֱ�Ӵ���InstallInlineHookʹ�õ�inlineSt����
	*/
	VOID UninstallInlineHook(IN InlineHookSt* inlineSt);

#ifdef __cplusplus
}
#endif


