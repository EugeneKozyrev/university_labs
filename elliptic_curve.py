import os
import hashlib
from cryptography.hazmat.primitives.asymmetric import ec
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import padding


def elgamal_encrypt(message, recipient_public_key):
    # Generate an ephemeral private key
    ephemeral_private_key = ec.generate_private_key(ec.SECP256K1(), default_backend())
    ephemeral_public_key = ephemeral_private_key.public_key()

    # Derive the shared secret
    shared_secret = ephemeral_private_key.exchange(ec.ECDH(), recipient_public_key)

    # Use the shared secret as the encryption key
    encryption_key = hashlib.sha256(shared_secret).digest()

    # Generate a random IV (Initialization Vector)
    iv = os.urandom(16)

    # Create a padder for PKCS7 padding
    padder = padding.PKCS7(algorithms.AES.block_size).padder()

    # Pad the message
    padded_message = padder.update(message.encode('utf-8')) + padder.finalize()

    # Encrypt the padded message
    cipher = Cipher(algorithms.AES(encryption_key), modes.CBC(iv), default_backend())
    encryptor = cipher.encryptor()
    encrypted_message = encryptor.update(padded_message) + encryptor.finalize()

    # Return the encrypted ciphertext, the ephemeral public key, and the IV
    return encrypted_message, ephemeral_public_key, iv


def elgamal_decrypt(ciphertext, ephemeral_public_key, iv, private_key):
    # Derive the shared secret using the ephemeral public key and the private key
    shared_secret = private_key.exchange(ec.ECDH(), ephemeral_public_key)

    # Use the shared secret as the decryption key
    decryption_key = hashlib.sha256(shared_secret).digest()

    # Decrypt the ciphertext
    cipher = Cipher(algorithms.AES(decryption_key), modes.CBC(iv), default_backend())
    decryptor = cipher.decryptor()
    padded_message = decryptor.update(ciphertext) + decryptor.finalize()

    # Create an unpadder for PKCS7 padding
    unpadder = padding.PKCS7(algorithms.AES.block_size).unpadder()

    # Unpad the decrypted message
    unpadded_message = unpadder.update(padded_message) + unpadder.finalize()

    # Return the decrypted message
    return unpadded_message.decode('utf-8')


# Generate a random private key
private_key = ec.generate_private_key(ec.SECP256K1(), default_backend())
public_key = private_key.public_key()

# Convert the public key to bytes for sharing
public_key_bytes = public_key.public_bytes(
    encoding=serialization.Encoding.PEM,
    format=serialization.PublicFormat.SubjectPublicKeyInfo
)

# Encrypt the word "Puppy"
encrypted_message, ephemeral_public_key, iv = elgamal_encrypt("supersecretstring", public_key)

# Convert the ephemeral public key to bytes for sharing
ephemeral_public_key_bytes = ephemeral_public_key.public_bytes(
    encoding=serialization.Encoding.PEM,
    format=serialization.PublicFormat.SubjectPublicKeyInfo
)

# Decrypt the ciphertext
decrypted_message = elgamal_decrypt(encrypted_message, ephemeral_public_key, iv, private_key)

print("Encrypted Message:", encrypted_message)
print("Decrypted Message:", decrypted_message)
