#include "StdAfx.h"
#include "FtpClient.h"

using namespace Anaheim;

/**
 * FTPクライアント
 */
FtpClient::FtpClient()
{
	this->ipAddress = nullptr;
	this->credential = nullptr;
}
// ----------------------------------------------------------------------------------------------------

String^ FtpClient::GetRootUri()
{
	return "ftp://" + this->ipAddress->ToString() + "/";
}
// ----------------------------------------------------------------------------------------------------

array<String^>^ FtpClient::GetDirectoryAndFileArray(System::String ^path, bool isDirectory)
{
	array<String^>^ result = gcnew array<String^>(0);

	System::Net::FtpWebResponse^ ftpRes = nullptr;
	System::IO::StreamReader^ stream = nullptr;

	try
	{
		System::Uri^ uri = gcnew System::Uri(path);
		FtpWebRequest^ ftpReq = dynamic_cast<System::Net::FtpWebRequest^>(System::Net::WebRequest::Create(uri));
		ftpReq->Credentials = this->credential;
		ftpReq->Method = System::Net::WebRequestMethods::Ftp::ListDirectoryDetails;
		ftpReq->KeepAlive = true;
		ftpReq->UsePassive = true;

		ftpRes = dynamic_cast<System::Net::FtpWebResponse^>(ftpReq->GetResponse());
		stream = gcnew System::IO::StreamReader(ftpRes->GetResponseStream());
		String^ temp = stream->ReadToEnd();

		String^ topChar = (isDirectory) ? "d" : "-";
		array<wchar_t>^ sepparator = { '\n' };
		for each (String^ str in temp->Split(sepparator))
		{
			if (!str->Equals(String::Empty) && str->Substring(0, 1) == topChar)
			{
				Array::Resize(result, result->Length + 1);
				result[result->Length - 1] = str->Substring(str->LastIndexOf(" ") + 1);
				result[result->Length - 1] = result[result->Length - 1]->Replace("\r", String::Empty);
			}
		}

		stream->Close();
		ftpRes->Close();
	}
	catch (Exception^)
	{
		if (stream != nullptr)
		{
			stream->Close();
		}
		if (ftpRes != nullptr)
		{
			ftpRes->Close();
		}
	}

	return result;
}
// ----------------------------------------------------------------------------------------------------

bool FtpClient::Connect(System::Net::IPAddress ^ip, System::String ^user, System::String ^pass)
{
	this->ipAddress = ip;
	this->credential = gcnew System::Net::NetworkCredential(user, pass);

	System::Net::FtpWebResponse^ ftpRes = nullptr;

	try
	{
		System::Uri^ uri = gcnew System::Uri(this->GetRootUri());
		System::Net::FtpWebRequest^ ftpReq = dynamic_cast<System::Net::FtpWebRequest^>(System::Net::WebRequest::Create(uri));
		ftpReq->Credentials = this->credential;
		ftpReq->Method = System::Net::WebRequestMethods::Ftp::PrintWorkingDirectory;
		ftpReq->KeepAlive = true;
		ftpReq->UsePassive = true;

		ftpRes = dynamic_cast<System::Net::FtpWebResponse^>(ftpReq->GetResponse());
		ftpRes->Close();
	}
	catch (Exception^)
	{
		if (ftpRes != nullptr)
		{
			ftpRes->Close();
		}
		return false;
	}

	return true;
}
// ----------------------------------------------------------------------------------------------------

bool FtpClient::Connect(System::Net::IPAddress ^ip, System::String ^pass)
{
	return this->Connect(ip, this->ANONYMITY_STRING, pass);
}
// ----------------------------------------------------------------------------------------------------

bool FtpClient::DisConnect()
{
	System::Net::FtpWebResponse^ ftpRes = nullptr;

	try
	{
		System::Uri^ uri = gcnew System::Uri(this->GetRootUri());
		System::Net::FtpWebRequest^ ftpReq = dynamic_cast<System::Net::FtpWebRequest^>(System::Net::WebRequest::Create(uri));
		ftpReq->Credentials = this->credential;
		ftpReq->Method = System::Net::WebRequestMethods::Ftp::PrintWorkingDirectory;
		ftpReq->KeepAlive = false;
		ftpReq->UsePassive = true;

		ftpRes = dynamic_cast<System::Net::FtpWebResponse^>(ftpReq->GetResponse());
		ftpRes->Close();
	}
	catch (Exception^)
	{
		if (ftpRes != nullptr)
		{
			ftpRes->Close();
		}
		return false;
	}

	return true;
}
// ----------------------------------------------------------------------------------------------------

bool FtpClient::Download(System::String ^remotePath, System::String ^localPath)
{
	System::Net::FtpWebResponse^ ftpRes = nullptr;
	System::IO::Stream^ stream = nullptr;
	System::IO::FileStream^ fStream = nullptr;

	try
	{
		array<String^>^ temp = remotePath->Split('/');
		String^ fileName = localPath->TrimEnd('\\') + "\\" + temp[temp->Length - 1]->Replace("%2f", String::Empty);

		System::Uri^ uri = gcnew System::Uri(remotePath);
		System::Net::FtpWebRequest^ ftpReq = dynamic_cast<System::Net::FtpWebRequest^>(System::Net::WebRequest::Create(uri));
		ftpReq->Credentials = this->credential;
		ftpReq->Method = System::Net::WebRequestMethods::Ftp::DownloadFile;
		ftpReq->KeepAlive = true;
		ftpReq->UsePassive = true;
		ftpReq->UseBinary = false;

		ftpRes = dynamic_cast<System::Net::FtpWebResponse^>(ftpReq->GetResponse());
		stream = ftpRes->GetResponseStream();
		fStream = gcnew System::IO::FileStream(fileName, System::IO::FileMode::Create, System::IO::FileAccess::Write);
		array<Byte>^ buff = gcnew array<Byte>(1024);
		while (true)
		{
			int size = stream->Read(buff, 0, buff->Length);
			if (size == 0) break;

			fStream->Write(buff, 0, size); 
		}

		fStream->Close();
		stream->Close();
		ftpRes->Close();
	}
	catch (Exception^)
	{
		if (fStream != nullptr)
		{
			fStream->Close();
		}
		if (stream != nullptr)
		{
			stream->Close();
		}
		if (ftpRes != nullptr)
		{
			ftpRes->Close();
		}
		return false;
	}

	return true;
}
// ----------------------------------------------------------------------------------------------------

bool FtpClient::Upload(System::String ^remotePath, System::String ^localPath)
{
	System::Net::FtpWebResponse^ ftpRes = nullptr;
	System::IO::Stream^ stream = nullptr;
	System::IO::FileStream^ fStream = nullptr;

	try
	{
		array<String^>^ temp = localPath->Split('\\');
		String^ fileName = remotePath + temp[temp->Length - 1];

		System::Uri^ uri = gcnew System::Uri(fileName);
		System::Net::FtpWebRequest^ ftpReq = dynamic_cast<System::Net::FtpWebRequest^>(System::Net::WebRequest::Create(uri));
		ftpReq->Credentials = this->credential;
		ftpReq->Method = System::Net::WebRequestMethods::Ftp::UploadFile;
		ftpReq->KeepAlive = true;
		ftpReq->UsePassive = true;
		ftpReq->UseBinary = false;
		
		stream = ftpReq->GetRequestStream();
		fStream = gcnew System::IO::FileStream(localPath, System::IO::FileMode::Open, System::IO::FileAccess::Read);
		array<Byte>^ buff = gcnew array<Byte>(1024);
		while (true)
		{
			int size = fStream->Read(buff, 0, buff->Length);
			if (size == 0) break;

			stream->Write(buff, 0, size); 
		}

		fStream->Close();
		stream->Close();

		ftpRes = dynamic_cast<System::Net::FtpWebResponse^>(ftpReq->GetResponse());
		ftpRes->Close();
	}
	catch (Exception^)
	{
		if (fStream != nullptr)
		{
			fStream->Close();
		}
		if (stream != nullptr)
		{
			stream->Close();
		}
		if (ftpRes != nullptr)
		{
			ftpRes->Close();
		}
		return false;
	}

	return true;
}
// ----------------------------------------------------------------------------------------------------

array<String^>^ FtpClient::GetDirectory(System::String ^path)
{
	return this->GetDirectoryAndFileArray(path, true);
}
// ----------------------------------------------------------------------------------------------------

array<String^>^ FtpClient::GetFileName(System::String ^path)
{
	return this->GetDirectoryAndFileArray(path, false);
}
// ----------------------------------------------------------------------------------------------------

int FtpClient::GetFileSize(System::String ^path)
{
	int result = 0;

	System::Net::FtpWebResponse^ ftpRes = nullptr;

	try
	{
		System::Uri^ uri = gcnew System::Uri(path);
		FtpWebRequest^ ftpReq = dynamic_cast<System::Net::FtpWebRequest^>(System::Net::WebRequest::Create(uri));
		ftpReq->Credentials = this->credential;
		ftpReq->Method = System::Net::WebRequestMethods::Ftp::GetFileSize;
		ftpReq->KeepAlive = true;
		ftpReq->UsePassive = true;

		ftpRes = dynamic_cast<System::Net::FtpWebResponse^>(ftpReq->GetResponse());
		result = (ftpRes->ContentLength % 1024 == 0) ? static_cast<int>(ftpRes->ContentLength / 1024) : static_cast<int>(ftpRes->ContentLength / 1024 + 1);
		ftpRes->Close();
	}
	catch (Exception^)
	{
		if (ftpRes != nullptr)
		{
			ftpRes->Close();
		}
		this->Connect(this->ipAddress, this->credential->UserName, this->credential->Password);		// 接続維持
	}

	return result;
}
// ----------------------------------------------------------------------------------------------------

DateTime FtpClient::GetFileDateTime(System::String ^path)
{
	DateTime result = DateTime(0);

	System::Net::FtpWebResponse^ ftpRes = nullptr;

	try
	{
		System::Uri^ uri = gcnew System::Uri(path);
		FtpWebRequest^ ftpReq = dynamic_cast<System::Net::FtpWebRequest^>(System::Net::WebRequest::Create(uri));
		ftpReq->Credentials = this->credential;
		ftpReq->Method = System::Net::WebRequestMethods::Ftp::GetDateTimestamp;
		ftpReq->KeepAlive = true;
		ftpReq->UsePassive = true;

		ftpRes = dynamic_cast<System::Net::FtpWebResponse^>(ftpReq->GetResponse());
		result = ftpRes->LastModified;
		ftpRes->Close();
	}
	catch (Exception^)
	{
		if (ftpRes != nullptr)
		{
			ftpRes->Close();
		}
		this->Connect(this->ipAddress, this->credential->UserName, this->credential->Password);		// 接続維持
	}

	return result;
}
// ----------------------------------------------------------------------------------------------------
