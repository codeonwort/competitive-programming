getInt = read `fmap` getLine :: IO Int
getInts = (map read . words) `fmap` getLine :: IO [Int]

-- ID:	691A (Fashion in Berland)
-- URL:	http://codeforces.com/problemset/problem/691/A

main = do
	n <- getInt
	xs <- getInts
	if n == 1
	then if xs == [1] then putStrLn "YES" else putStrLn "NO"
	else if (filter (==0) xs) == [0] then putStrLn "YES" else putStrLn "NO"
