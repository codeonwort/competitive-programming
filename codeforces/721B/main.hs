-- ID:  721B (Passwords)
-- URL: http://codeforces.com/problemset/problem/721/B

import Data.List
import Data.Maybe
import Control.Monad

getInt = read `fmap` getLine :: IO Int
compareLength x y = compare (length x) (length y)

main = do
	[n, k] <- (map read . words) `fmap` getLine :: IO [Int]
	passwords <- sortBy compareLength `fmap` replicateM n getLine
	validPwd <- getLine
	let fails = length $ takeWhile (\p -> length p < length validPwd) passwords
	let fails_time = fails + ((fails `div` k) * 5)
	putStr $ show (fails_time + 1) -- best
	putChar ' '
	let sameLenWords = (takeWhile (\p -> length p == length validPwd) $ drop fails passwords) 
	let fails' = length sameLenWords - 1 + fails
	let fails_time' = fails' + ((fails' `div` k) * 5)
	print (fails_time' + 1) -- worst
