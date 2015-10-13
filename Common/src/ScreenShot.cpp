#include "gdiplus.h" 
using namespace Gdiplus;
#pragma comment(lib,"gdiplus.lib")

bool CaptureScreen( UINT quality)
{
	HDC hDCSrc = ::GetDC(NULL);
	int nBitPerPixel = GetDeviceCaps(hDCSrc, BITSPIXEL);//����λ
	int nWidth = GetDeviceCaps(hDCSrc, HORZRES);//// �õ���ǰ��ʾ�豸��ˮƽ������
	int nHeight = GetDeviceCaps(hDCSrc, VERTRES);
	CImage cImage;//ʹ��CImage��ʡ�ö��ͼ�Ĵ���
	cImage.Create(nWidth, nHeight, nBitPerPixel);
	BitBlt(cImage.GetDC(), 0, 0, nWidth, nHeight, hDCSrc, 0, 0, SRCCOPY);
	::ReleaseDC(NULL, hDCSrc);
	cImage.ReleaseDC();//��ͼ�Ĵ��뵽����ͽ�����

	COleStreamFile cImgStream;
	cImgStream.CreateMemoryStream(NULL);
	cImage.Save(cImgStream.GetStream(), Gdiplus::ImageFormatBMP);//��2��������д����
	Image image(cImgStream.GetStream());//��������Graphics::Image����
	cImgStream.Close();

	CLSID encoderClsid;
	GetEncoderClsid(L"image/jpeg", &encoderClsid);//��ȡ����CLSID
	EncoderParameters encoderParameters;//�����⼸������Ĳ�����ֻ֪��һ��.ValueΪѹ���ʣ������Ĳ�����
	encoderParameters.Count = 1; 
	encoderParameters.Parameter[0].Guid = EncoderQuality; 
	encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong; 
	encoderParameters.Parameter[0].NumberOfValues = 1; 
	encoderParameters.Parameter[0].Value = &quality;
	image.Save(L"error.jpg", &encoderClsid, &encoderParameters); //Ҳ��ֱ��д��ͼƬ�ļ�
	 
	return true;
}