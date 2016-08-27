import Data.Int

getInt64 = read `fmap` getLine :: IO Int64
isqrt :: Int64 -> Int64
isqrt = floor . sqrt . fromIntegral
isSquare x = y * y == x where y = isqrt x

-- ID:	707C (Pythagorean Triples)
-- URL:	http://codeforces.com/problemset/problem/707/C

main = do
	n <- getInt64
	solve n

solve n = do
	if n <= 2
	then print (-1)
	else if odd n
	then do
		let n2 = n*n
		let a = n2 `div` 2
		let b = a + 1
		putStrLn $ show a ++ " " ++ show b
	else do
		let n2 = (n `div` 2)^2
		let a = n2 - 1
		let b = n2 + 1
		putStrLn $ show a ++ " " ++ show b
