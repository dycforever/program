openssl x509 -x509toreq -in fd.crt -out fd.csr -signkey fd.key

create cert:
openssl x509 -req -days 365 -in fd.csr -signkey fd.key -out fd.crt

create cert without csr:
openssl req -new -x509 -days 365 -key fd.key -out fd.crt

create cert without interactive:
openssl req -new -x509 -days 365 -key fd.key -out fd.crt \
    -subj "/C=GB/L=London/O=Feisty Duck Ltd/CN=www.feistyduck.com"""

!!!
When a certificate contains alternative names, all common names are ignored. Newer
certificates produced by CAs may not even include any common names. For that
reason, include all desired hostnames on the alternative names list.
!!!

subjectAltName = DNS:*.feistyduck.com, DNS:feistyduck.com

openssl x509 -req -days 365 \
    -in fd.csr -signkey fd.key -out fd.crt \
    -extfile fd.ext

The Basic Constraints extension is used to mark certificates as belonging to a CA, giving them
the ability to sign other certificates. Non-CA certificates will either have this extension omit-
ted or will have the value of CA set to FALSE . 

The Key Usage (KU) and Extended Key Usage (EKU) extensions restrict what a certificate can
be used for.
if the extensions are not present, there are no use restrictions.

RL Distribution Points extension lists the addresses where the CA’s Certificate Revoca-
tion List (CRL) information can be found

The Authority Information Access (AIA) extension usually contains two important pieces of
information. First, it lists the address of the CA’s Online Certificate Status Protocol (OCSP)
responder

The value specified in the Authority Key Identifier ex-
tension of a certificate must match the value specified in the Subject Key Identifier extension
in the issuing certificate.

PKCS#7 certificate(s)
seen with .p7b and .p7c extensions and can include the entire
certificate chain as needed.

PKCS#12 (PFX) key and certificate(s)
A complex format that can store and protect a server key along with an entire certificate
chain. It’s commonly seen with .p12 and .pfx extensions.

conversion:
openssl x509 -inform PEM -in fd.pem -outform DER -out fd.der

openssl ciphers -V switch to
request extra-verbose output. In this mode, the output will also contain suite IDs,
