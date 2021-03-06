//덧셈, 뺄셈, 곱셈
(a + b) % M = ((a % M) + (b % M)) % M
(a - b) % M = ((a % M) - (b % M) + M) % M
(a * b) % M = ((a % M) * (b % M)) % M

//나눗셈
modInv(b, M) = (b ^ (M - 2)) % M
(a / b) % M = (a * modInv(b, M)) % M