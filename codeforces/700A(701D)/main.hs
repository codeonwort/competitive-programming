-- ID:	701D (As Fast As Possible)
-- URL:	http://codeforces.com/contest/701/problem/D

main = do
	ps@[n, l, v1, v2, k] <- (map read . words) `fmap` getLine :: IO [Int]
	let ps' = map fromIntegral ps :: [Double]
	print $ solve ps'

solve :: [Double] -> Double
solve [n, l, v1, v2, k] = t1 + x where
	m = fromIntegral (ceiling (n / k)) :: Double
	v3 = (v2 - v1) / (v2 + v1)
	x = l / (v2 + (m-1)*(v1 * (1+ v3)))
	t1 = (l - v2*x) / v1
