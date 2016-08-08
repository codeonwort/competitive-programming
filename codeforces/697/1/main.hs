-- ID:	697A (Pineapple Incident)
-- URL:	http://codeforces.com/problemset/problem/697/A

main = do
	[t,s,x] <- (map read . words) `fmap` getLine :: IO [Int]
	if x < t
	then putStrLn "NO"
	else if (x-t) `mod` s == 0
	then putStrLn "YES"
	else if (x-t-1) `mod` s == 0 && x /= t + 1
	then putStrLn "YES"
	else putStrLn "NO"
