/*
 * Utility
 */

char *net_b64e(char *s_in, char *s_out);
int net_sprintq(char *buf,char *s);

/*
 * Main interface
 */

int net_get(char *data);
int net_init();
void net_quit();
