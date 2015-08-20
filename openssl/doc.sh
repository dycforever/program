openssl x509 -x509toreq -in fd.crt -out fd.csr -signkey fd.key

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

#compare speed
openssl speed rc4 aes rsa ecdh sha
openssl speed -evp aes-128-cbc
openssl speed aes-128-cbc


