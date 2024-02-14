def is_prime(num):
  """
  Checks if a number is prime.

  Args:
      num: The number to check.

  Returns:
      True if the number is prime, False otherwise.
  """
  if num <= 1:
    return False
  if num <= 3:
    return True
  if num % 2 == 0 or num % 3 == 0:
    return False
  i = 5
  while i * i <= num:
    if num % i == 0 or num % (i + 2) == 0:
      return False
    i += 6
  return True

def find_primes_up_to(n):
  """
  Finds all prime numbers less than or equal to a given number.

  Args:
      n: The upper limit for prime numbers.

  Returns:
      A list of all prime numbers less than or equal to n.
  """
  primes = []
  num = 2
  while num <= n:
    if is_prime(num):
      primes.append(num)
    num += 1
  return primes

# Example usage
n = 10**5 # Find primes up to 100
primes = find_primes_up_to(n)
print(f"Prime numbers less than or equal to {n}: {len(primes)}")
