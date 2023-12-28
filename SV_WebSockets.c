#include "open62541.h"
#include <libwebsockets.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <netdb.h>
//#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>  // inet_addr
#include <unistd.h>
#include <pthread.h>


static int ActivateWebSocketStreams_firstTime = 1;
extern char g_argv_ip[255];
static int sockfd;
static struct hostent* he;
static struct sockaddr_in websocket_addr_data;        /* connector's address information */


#define PORT 7681

int ActivateWebSocketStreams(UA_Server *);

// Every time there is a change in the data (via MonitoredItems),
// it will call this function to push the entire data set in the OPCAddress space via localhost:7681
int ActivateWebSocketStreams(UA_Server *uaServer)
{
return 0;
   if (ActivateWebSocketStreams_firstTime == 1)
   {
        ActivateWebSocketStreams_firstTime = 0;

	if ((he = gethostbyname(g_argv_ip)) == NULL)
        {
                //herror("gethostbyname");
                exit(-1);
        }

        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
                perror("SV_WebSockets.c : socket creation failed");
                exit(-1);
        }
        else
                printf("SV_WebSockets.c : create socket(sockfd) success \n");

        bzero(&websocket_addr_data, sizeof(websocket_addr_data));     /* zero the rest of the struct */

	printf("g_arv_ip is %s \n", g_argv_ip);

	//websocket_addr_data.sin_addr = *((struct in_addr *) he-> h_addr);
        websocket_addr_data.sin_addr.s_addr = htonl(INADDR_ANY);
        websocket_addr_data.sin_port = htons(PORT);    /* short, network byte order */
        websocket_addr_data.sin_family = AF_INET;      /* host byte order */


	printf("Trying to open outgoing port %s:%d ... \n", g_argv_ip, PORT);
   	if (connect(sockfd, (struct sockaddr*)&websocket_addr_data, sizeof(websocket_addr_data)) < 0)
   	{
        	perror("SV_WebSockets.c : connection to port failed");
        	exit(-1);
   	}
   	else
        	printf("SV_WebSockets.c : connect(sockfd) to port %s success \n", PORT);
    }

    printf("SV_WebSockets.c : prepare data stream and write to port %s \n", PORT);





/*
        struct lws_context_creation_info info;

        lws_context_info_defaults(&info, "example-policy.json");
        //lws_cmdline_option_handle_builtin(argc, argv, &info);
        signal(SIGINT, sigint_handler);

        lwsl_user("LWS Secure Streams Server\n");

        info.early_smd_cb		= smd_cb;
        info.early_smd_class_filter	= LWSSMDCL_SYSTEM_STATE;

        cx = lws_create_context(&info);
        if (!cx) {
                lwsl_err("lws init failed\n");
                return 1;
        }

        lws_context_default_loop_run_destroy(cx);

        // process ret 0 if actual is as expected (0, or--expected-exit 123)

        return lws_cmdline_passfail(argc, argv, test_result);
*/
}

