#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    char *advice[] = {
        "Take smaller bites\r\n",
        "Go word: inappropriate\r\n",
        "Just for today, be honest. Tell your what you *really* think\r\n",
        "You might want to rethink that haircut\r\n"
    };

    int listener_d = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = (in_port_t)htons(30000);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listener_d, (struct sockaddr *) &name, sizeof(name)) == -1)
        error("Can't bind the port");
    int reuse = 1;
    if (setsockopt(listener_d, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) == -1)
        error("Can't set the reuse option on the socket");
    listen(listener_d, 10);
    puts("Waiting for connection");
    while (1)
    {
        struct sockaddr_storage client_addr;
        unsigned int address_size = sizeof(client_addr);
        int connect_d = accept(listener_d, (struct sockaddr*)&client_addr, &address_size);
        char *msg = advice[rand() % 5];
        send(connect_d, msg, strlen(msg), 0);
        close(connect_d);
    }
    return 0;
}