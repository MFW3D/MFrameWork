#include "UDTServerMgr.h"
using namespace std;
void* UDTServer::recvdata(void* usocket)
{
	int addrlen = sizeof(clientaddr);
	while (true)
	{
		if (UDT::INVALID_SOCK == (recver = UDT::accept(serv, (sockaddr*)&clientaddr, &addrlen)))
		{
			cout << "accept: " << UDT::getlasterror().getErrorMessage() << endl;
			return 0;
		}

		char clienthost[NI_MAXHOST];
		char clientservice[NI_MAXSERV];
		getnameinfo((sockaddr *)&clientaddr, addrlen, clienthost, sizeof(clienthost), clientservice, sizeof(clientservice), NI_NUMERICHOST | NI_NUMERICSERV);
		cout << "new connection: " << clienthost << ":" << clientservice << endl;

		UDTSOCKET recver = *(UDTSOCKET*)usocket;
		delete (UDTSOCKET*)usocket;

		char* data;
		int size = 100000;
		data = new char[size];

		while (true)
		{
			int rsize = 0;
			int rs;
			while (rsize < size)
			{
				int rcv_size;
				int var_size = sizeof(int);
				UDT::getsockopt(recver, 0, UDT_RCVDATA, &rcv_size, &var_size);
				if (UDT::ERROR == (rs = UDT::recv(recver, data + rsize, size - rsize, 0)))
				{
					cout << "recv:" << UDT::getlasterror().getErrorMessage() << endl;
					break;
				}

				rsize += rs;
			}

			if (rsize < size)
				break;
		}

		delete[] data;

		UDT::close(recver);

	}
}
int UDTServer::Start(int port)
{
	addrinfo hints;
	addrinfo* res;

	memset(&hints, 0, sizeof(struct addrinfo));

	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	//hints.ai_socktype = SOCK_DGRAM;

	string service(std::to_string(port));

	if (0 != getaddrinfo(NULL, service.c_str(), &hints, &res))
	{
		cout << "illegal port number or port is busy.\n" << endl;
		return 0;
	}

	 serv = UDT::socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	// UDT Options
	//UDT::setsockopt(serv, 0, UDT_CC, new CCCFactory<CUDPBlast>, sizeof(CCCFactory<CUDPBlast>));
	//UDT::setsockopt(serv, 0, UDT_MSS, new int(9000), sizeof(int));
	//UDT::setsockopt(serv, 0, UDT_RCVBUF, new int(10000000), sizeof(int));
	//UDT::setsockopt(serv, 0, UDP_RCVBUF, new int(10000000), sizeof(int));

	if (UDT::ERROR == UDT::bind(serv, res->ai_addr, res->ai_addrlen))
	{
		cout << "bind: " << UDT::getlasterror().getErrorMessage() << endl;
		return 0;
	}

	freeaddrinfo(res);

	cout << "server is ready at port: " << service << endl;

	if (UDT::ERROR == UDT::listen(serv, 10))
	{
		cout << "listen: " << UDT::getlasterror().getErrorMessage() << endl;
		return 0;
	}
	return 0;
}

void UDTServer::Stop()
{
	UDT::close(serv);
}


void UDTServerMgr::StartUdt(std::vector<UDTStartInfo>& startInfo)
{

}
