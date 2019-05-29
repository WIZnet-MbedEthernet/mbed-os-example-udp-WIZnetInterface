#include "mbed.h"
#include "WIZnetInterface.h"
// Network interface
NetworkInterface *net;

// Socket demo
int main() {
  int remaining;
  int rcount;
  char *p;
  char *buffer = new char[256];
  //char *buffer = new char[2024];
  nsapi_size_or_error_t result;
  int index = 0, find_result = 0;
  char external_ip[24];
#if 1

  NetworkInterface *net1;
  nsapi_size_or_error_t send_result;
  nsapi_size_or_error_t r_result;
  // wiznet init
  static uint8_t WIZNET_DEFAULT_TESTMAC[6] = {0x00, 0x08, 0xdc,
                                              0x19, 0x85, 0xa8};
  char Wiz_ip[24] = "192.168.0.6";
  char Wiz_gateway[24] = "192.168.0.1";
  char Wiz_netmask[24] = "255.255.255.0";
  char Wiz_dnsaddr[24] = "8.8.8.8";
  const char Wiz_dest_ip[12] = "192.168.0.2";
  uint16_t Wiz_UDP_PORT = 5000;
  uint16_t Wiz_UDP_PORT1 = 5001;
  uint16_t Wiz_UDP_PORT2 = 5002;
  static WIZnetInterface eth1(WIZNET_MOSI, WIZNET_MISO, WIZNET_SCK, WIZNET_CS,
                              WIZNET_RESET);
  //static WIZnetInterface eth1;
  SocketAddress Wiz_dest;
  SocketAddress recv_addr;
  Wiz_dest.set_ip_address(Wiz_dest_ip);
  Wiz_dest.set_port(Wiz_UDP_PORT1);
  char buff[256];
  int cnt = 0;

  // Bring up the ethernet interface
  printf("Mbed OS Socket example\n");

#ifdef MBED_MAJOR_VERSION
  printf("Mbed OS version: %d.%d.%d\n\n", MBED_MAJOR_VERSION,
         MBED_MINOR_VERSION, MBED_PATCH_VERSION);
#endif

  printf("Network info \r\n");
  printf("ip      : %s \r\n", Wiz_ip);
  printf("gateWay : %s \r\n", Wiz_gateway);
  printf("netmask : %s \r\n", Wiz_netmask);
  printf("dns     : %s \r\n", Wiz_dnsaddr);
  eth1.init(WIZNET_DEFAULT_TESTMAC, Wiz_ip, Wiz_netmask, Wiz_gateway);
  eth1.setDnsServerIP(Wiz_dnsaddr);

  net1 = &eth1;

  UDPSocket UDP_socket;
  UDPSocket UDP_socket1;
  UDPSocket UDP_socket2;
  printf("UDP Socket open \n");
  UDP_socket.open(net1);
  UDP_socket1.open(net1);
  UDP_socket2.open(net1);

  printf("UDP Socket bind \n");
  UDP_socket.bind(Wiz_UDP_PORT);
  printf("UDP send to \n");

  send_result = UDP_socket1.sendto(Wiz_dest, "test!\r\n", strlen("test!\r\n"));
  printf("UDP send result[%d]: %s\n", send_result, "test!\r\n");
  printf("_____________________________ \r\n");

  while (1) {
    r_result = UDP_socket.recvfrom(&recv_addr, buff, 256);
    if (r_result > 0) {
      printf("[%d]recv[%s]:[%d] : %s \n",r_result, recv_addr.get_ip_address(), recv_addr.get_port(), buff);
      send_result = UDP_socket1.sendto(recv_addr, buff, strlen(buff));
      printf("UDP send result[%d]: %s\r\n", send_result, buff);
      printf("_____________________________ \r\n");
    }
  }
}
