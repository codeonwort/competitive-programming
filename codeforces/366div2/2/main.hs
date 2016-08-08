getInt = read `fmap` getLine :: IO Int

main = do
	n <- getInt
	xs <- (map read . take n . words) `fmap` getContents :: IO [Int]
	solve xs 0

solve [] acc = return ()
solve (x:xs) acc
	| even x = do
		print $ if even acc then 1 else 2
		solve xs (acc+1)
	| otherwise = do
		print $ if even acc then 2 else 1
		solve xs acc
