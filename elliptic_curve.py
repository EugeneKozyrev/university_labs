from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.asymmetric import ec
from cryptography.hazmat.primitives import serialization, hashes
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC
from cryptography.hazmat.primitives.padding import PKCS7
from os import urandom


def generate_key_pair():
    # Generate an elliptic curve key pair
    private_key = ec.generate_private_key(
        ec.SECP256K1(), default_backend()
    )
    public_key = private_key.public_key()

    # Serialize the keys
    private_key_bytes = private_key.private_bytes(
        encoding=serialization.Encoding.PEM,
        format=serialization.PrivateFormat.PKCS8,
        encryption_algorithm=serialization.NoEncryption()
    )
    public_key_bytes = public_key.public_bytes(
        encoding=serialization.Encoding.PEM,
        format=serialization.PublicFormat.SubjectPublicKeyInfo
    )

    return private_key_bytes, public_key_bytes


def encrypt_message(message, public_key_bytes):
    # Deserialize the public key
    public_key = serialization.load_pem_public_key(
        public_key_bytes,
        backend=default_backend()
    )

    # Generate a random shared secret
    private_key = ec.generate_private_key(
        ec.SECP256K1(), default_backend()
    )
    shared_secret = private_key.exchange(ec.ECDH(), public_key)

    # Derive a symmetric encryption key
    salt = b'salt'  # Change this to a random value for each encryption
    kdf = PBKDF2HMAC(
        algorithm=hashes.SHA256(),
        length=32,
        salt=salt,
        iterations=100000,
        backend=default_backend()
    )
    key = kdf.derive(shared_secret)

    # Generate a random initialization vector (IV)
    iv = urandom(16)  # Change this to a random value for each encryption

    # Pad the message with PKCS7
    padder = PKCS7(algorithms.AES.block_size).padder()
    padded_message = padder.update(message) + padder.finalize()

    # Encrypt the padded message using AES-CBC
    cipher = Cipher(
        algorithms.AES(key),
        modes.CBC(iv),
        backend=default_backend()
    )
    encryptor = cipher.encryptor()
    ciphertext = encryptor.update(padded_message) + encryptor.finalize()

    return ciphertext, salt, iv


def decrypt_message(ciphertext, private_key_bytes, salt, iv):
    # Deserialize the private key
    private_key = serialization.load_pem_private_key(
        private_key_bytes,
        password=None,
        backend=default_backend()
    )

    # Derive the shared secret using the private key and peer's public key
    public_key = private_key.public_key()
    shared_secret = private_key.exchange(ec.ECDH(), public_key)

    # Derive the symmetric encryption key using the shared secret
    kdf = PBKDF2HMAC(
        algorithm=hashes.SHA256(),
        length=32,
        salt=salt,
        iterations=100000,
        backend=default_backend()
    )
    key = kdf.derive(shared_secret)

    # Decrypt the ciphertext using AES-CBC
    cipher = Cipher(
        algorithms.AES(key),
        modes.CBC(iv),
        backend=default_backend()
    )
    decryptor = cipher.decryptor()
    decrypted_message = decryptor.update(ciphertext) + decryptor.finalize()

    # Unpad the decrypted message
    unpadder = PKCS7(algorithms.AES.block_size).unpadder()
    unpadded_message = unpadder.update(decrypted_message) + unpadder.finalize()

    return unpadded_message


# Example usage
private_key, public_key = generate_key_pair()

message = b'This is a secret message.'
ciphertext, salt, iv = encrypt_message(message, public_key)
decrypted_message = decrypt_message(ciphertext, private_key, salt, iv)

print('Original message:', message)
print('Decrypted message:', decrypted_message)
