-- ID:	702D (Road To Post Office)
-- URL:	http://codeforces.com/contest/702/problem/D

getInt = read `fmap` getLine :: IO Integer
getInts = (map read . words) `fmap` getLine :: IO [Integer]

main = do
	ary@[d,k,a,b,t] <- getInts
	print $ solve ary

solve :: [Integer] -> Integer
solve [d,k,a,b,t]
	| d <= k = d*a
	| t + k*a >= k*b = k*a + (d-k)*b
	| otherwise = car_time + f (d - k*m) where
		m = d `div` k
		car_time = (m-1)*t + m*a*k
		f d
			| d == 0 = 0
			| otherwise = min (d*a + t) (d*b)
