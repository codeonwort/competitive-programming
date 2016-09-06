-- ID:  691B (s-palindrome)
-- URL: http://codeforces.com/problemset/problem/691/B

import Data.List

pairs = [
	('A','A'), ('b','d'), ('d','b'), ('H','H'), ('I','I'),
	('M','M'), ('O','O'), ('o','o'), ('p','q'), ('q','p'),
	('T','T'), ('U','U'), ('V','V'), ('v','v'), ('W','W'),
	('w','w'), ('X','X'), ('x','x'), ('Y','Y')
	]

mirror [] = []
mirror (x:xs) = case lookup x pairs of
	Nothing -> '?' : mirror xs
	Just y -> y : mirror xs

palindrome str = mirror left == reverse right where
	n = length str
	m = n `div` 2
	left = if odd n then take (m+1) str else take m str
	right = drop m str

main = do
	str <- getLine
	if palindrome str
	then putStrLn "TAK"
	else putStrLn "NIE"
