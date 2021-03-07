const int MAX_BUF = 1000;
char* Buffer = malloc(MAX_BUF);

int length = 0;
length += snprintf(Buffer+length, MAX_BUF-length, "Hello World");
length += snprintf(Buffer+length, MAX_BUF-length, "Good Morning");
length += snprintf(Buffer+length, MAX_BUF-length, "Good Afternoon");
