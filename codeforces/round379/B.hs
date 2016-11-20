-- Codeforces Round #379 (Div. 2)
-- http://codeforces.com/contest/734

-- ID: 734B (Anton and Digits)

main = do
	[k2, k3, k5, k6] <- (map read . words) `fmap` getLine :: IO [Integer]
	let x = minimum [k2, k5, k6]
	let y = minimum [k3, k2 - x]
	print $ x*256 + y*32
