-- ID:  714B (Filya and Homework)
-- URL: http://codeforces.com/problemset/problem/714/B

import Data.List

getInt = read `fmap` getLine :: IO Int

main = do
	n <- getInt
	xs <- (map read . take n . words) `fmap` getContents :: IO [Int]
	putStrLn $ (judge . collect) xs

collect xs = f xs [] where
	f [] acc = Just acc
	f (x:xs) acc
		| x `elem` acc    = f xs acc
		| length acc == 3 = Nothing
		| otherwise       = f xs (x:acc)

judge Nothing = "NO"
judge (Just [x]) = "YES"
judge (Just [x,y]) = "YES"
judge (Just [x,y,z])
	| arithmeticSeq (sort [x,y,z]) = "YES"
	| otherwise = "NO"

arithmeticSeq [x,y,z]
	| y-x == z-y = True
	| otherwise  = False
