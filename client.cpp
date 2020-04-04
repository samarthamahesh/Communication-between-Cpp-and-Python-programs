#include <bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define PORT 8080
#define MAX_LEN 1000

using namespace std;

int main(int argc, char const *argv[]) {
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char *hello = (char *)malloc(sizeof(char)*MAX_LEN);
	cout << "Your message: ";
	fgets(hello, MAX_LEN, stdin);
	char buffer[1024] = {0};
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		cout << "Socket creation error" << endl;
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)	{
		cout << "Invalid address/ Address not supported" << endl;
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		cout << "Connection Failed" << endl;
		return -1;
	}
	send(sock , hello , strlen(hello) , 0);
	cout << "Message sent" << endl;

	valread = read(sock, buffer, 1024);
	cout << "Message from server: " << buffer << endl;
	return 0;
}