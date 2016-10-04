-- ID:  722B (Verse Pattern)
-- URL: http://codeforces.com/problemset/problem/722/B

import Control.Monad

getInt = read `fmap` getLine :: IO Int

containsVowel str = any (`elem` "aeiouy") str
countVowel str = length (filter (`elem` "aeiouy") str)

main = do
	n <- getInt
	patterns <- (map read . words) `fmap` getLine :: IO [Int]
	lines <- replicateM n getLine
	results <- forM (zip patterns lines) $ \(pat, line) -> do
		let cands = filter containsVowel (words line)
		if pat == sum (map countVowel cands)
		then return True
		else return False
	if all id results
	then putStrLn "YES"
	else putStrLn "NO"
