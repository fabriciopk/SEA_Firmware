#include <dynamixel.h>
#include <cstdlib>
#include <unistd.h>
#include <signal.h>
#include <cstdio>

void signal_callback_handler(int signum)
{
  printf("Caught signal %d\n", signum);
  dxl_terminate();
  exit(signum);
}

int main(int argc, char *argv[])
{
  signal(SIGINT, signal_callback_handler);

  if (dxl_initialize(0,1) == 0)
  {
    printf( "Failed to open USB2Dynamixel!\n" );
    return -1;
  }
  int id = atoi(argv[1]);;
  while (true)
  {
      int pos = dxl_read_word(id, 0x24);
      usleep(1000);
     //dxl_ping(id);
      int result = dxl_get_result();
      if (result != 1) pos = -1;
      printf("%d: %d\n", id, pos);
  }

  return EXIT_SUCCESS;
}

