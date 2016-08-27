import Data.Maybe
import Control.Monad

-- ID:	707A (Brain's Photos)
-- URL:	http://codeforces.com/problem/707/A

getInt = read `fmap` getLine :: IO Int
getInts = (map read . words) `fmap` getLine :: IO [Int]
getChars = (map head . words) `fmap` getLine :: IO [Char]

main = do
	[n,m] <- getInts
	bmp <- replicateM n getChars
	if isGreyscale bmp then putStrLn "#Black&White" else putStrLn "#Color"

isGreyscale rows = all grey rows where
	grey row = all (\c -> c `elem` "WGB") row
