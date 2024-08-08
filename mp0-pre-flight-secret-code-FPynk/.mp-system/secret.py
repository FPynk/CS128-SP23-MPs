import hashlib

with open('netid.txt') as f:
    netid = f.readline()

# Generate secret
secret = hashlib.sha256(netid.strip().encode()).hexdigest()[:5]

with open('secret.txt', 'w') as f:
    if len(netid) != 0 and not netid.isspace():
        f.write(secret)
    else:
        f.write('netid.txt is empty')
