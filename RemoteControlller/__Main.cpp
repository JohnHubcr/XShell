#include "RemoteControllerFrameWork.h"

#define REMOTECONTROLLER_CMD_SIZE  1024
int main()
{
	
	if (!G_RemoteFrameWork.Initialize())
	{
		printf("���ƶ˳�ʼ��ʧ��\n");
	}
	G_RemoteFrameWork.Run();
	char Command[REMOTECONTROLLER_CMD_SIZE];

	while (TRUE)
	{
		G_RemoteFrameWork.OnPrintLocation();
		gets(Command);
		G_RemoteFrameWork.OnCommand(Command);
	}


}