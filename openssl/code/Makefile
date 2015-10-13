export CPLUS_INCLUDE_PATH=/home/dingyc/tools/openssl-1.0.1h/include/
export CPPFLAGS=\
		 -finline-functions \
		 -g \
		 -pipe \
		 -W \
		 -Wall \
		 -Werror \
		 -fPIC -g

export LDFLAGS=-L/home/dingyc/tools/openssl-1.0.1h/lib/ -lpthread -lssl -lcrypto -ldl
export LIBRARY_PATH=/home/dingyc/tools/openssl-1.0.1h/lib/
targets=bio_client ssl_client ssl_server https_client PKEY_cipher evp_cipher ngx ocsp

all:$(targets)

bio_client:bio_client.cpp
	g++ -o $@ $(CPPFLAGS) -I $(CPLUS_INCLUDE_PATH) $^ -L$(LIBRARY_PATH) $(LDFLAGS)

ssl_client:ssl_client.cpp
	g++ -o $@ $(CPPFLAGS) -I $(CPLUS_INCLUDE_PATH) $^ -L$(LIBRARY_PATH) $(LDFLAGS)

ssl_server:ssl_server.cpp
	g++ -o $@ $(CPPFLAGS) -I $(CPLUS_INCLUDE_PATH) $^ -L$(LIBRARY_PATH) $(LDFLAGS)

https_client:https_client.cpp
	g++ -o $@ $(CPPFLAGS) -I $(CPLUS_INCLUDE_PATH) $^ -L$(LIBRARY_PATH) $(LDFLAGS)

evp_cipher:evp_cipher.cpp
	g++ -o $@ $(CPPFLAGS) -I $(CPLUS_INCLUDE_PATH) $^ -L$(LIBRARY_PATH) $(LDFLAGS)

PKEY_cipher:PKEY_cipher.cpp
	g++ -o $@ $(CPPFLAGS) -I $(CPLUS_INCLUDE_PATH) $^ -L$(LIBRARY_PATH) $(LDFLAGS)

ngx:ngx.c
	gcc -o $@ $(CPPFLAGS) -I $(CPLUS_INCLUDE_PATH) $^ -L$(LIBRARY_PATH) $(LDFLAGS)

ocsp:ocsp.c
	gcc -o $@ $(CPPFLAGS) -I $(CPLUS_INCLUDE_PATH) $^ -L$(LIBRARY_PATH) $(LDFLAGS)

.PHONY: clean
clean:
	rm -rf $(targets)


