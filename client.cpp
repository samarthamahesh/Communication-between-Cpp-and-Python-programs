#include <iostream>
#include <boost/asio.hpp>

static const unsigned PORT = 8080;

int main(int argc, char const *argv[]) {
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::socket socket(io_service);
	
	socket.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), PORT));
	std::string hello;
	std::cout << "Your message: ";
	std::getline(std::cin, hello);
	
	boost::system::error_code error;
	boost::asio::write(socket, boost::asio::buffer(hello), error);
	if(!error) {
		std::cout << "Message sent" << std::endl;
	} else {
		std::cout << "Send failed: " << error.message() << std::endl;
	}

	boost::asio::streambuf receive_buffer;
	boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);
	if(error && error != boost::asio::error::eof) {
		std::cout << "Receive failed: " << error.message() << std::endl;
	} else {
		std::string data = boost::asio::buffer_cast<const char*>(receive_buffer.data());
		std::cout << data << std::endl;
	}
}
