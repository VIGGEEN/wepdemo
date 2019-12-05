# WEP Demo
A demo showcasing the weakness of the WEP (Wired Equivalent Protocol).

### Build
>Run cmake from project root with the desired output path
>
### Documentation
NOTE: All files are required to be in bitmap format of bitdepth 24 and be 512x512 in resolution.
>
**Generate keystream**
>Generates a keystream of size 512x512 and writes it to file
>
**Encrypt plaintext**
>Encrypts a plaintext using previously generated keystream and writes the resulting ciphertext to file
>
**Decrypt plaintext**
>Decrypts a plaintext using previously generated keystream and writes the resulting plaintext to file
>
**XOR ciphertexts**
>XOR's two ciphertexts and writes the result to file
>
**XOR cipherguess**
>XOR's a ciphertext with a guesstext and writes the result to file
>