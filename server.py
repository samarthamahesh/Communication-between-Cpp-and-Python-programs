from twisted.internet.protocol import Factory, Protocol
from twisted.internet.endpoints import TCP4ServerEndpoint
from twisted.internet import reactor

class QOTDFactory(Factory):
    def buildProtocol(self, addr):
        print(addr)
        return QOTD()

class QOTD(Protocol):

    def dataReceived(self, data):
        print('Message from client:', data.decode('ascii'), "\n")
        msg = 'Thanks for connecting!!'
        self.transport.write(msg.encode('ascii'))
        self.transport.loseConnection()

if __name__ == '__main__':
    endpoint = TCP4ServerEndpoint(reactor, 8080)
    endpoint.listen(QOTDFactory())
    reactor.run()
