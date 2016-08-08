import Control.Monad
import Data.Char
import Prelude hiding (succ)

-- Problem ID:	5
-- URL:			http://www.spoj.com/problems/PALIN/

divide :: String -> (String, String, String)
divide n
	| len `mod` 2 == 0 = (ls, [], m:rs)
	| otherwise = (ls, [m], rs) where
	len = length n
	(ls, m:rs) = splitAt (len `div` 2) n

np :: String -> String
np n
	| n == "9" = "11"
	| m == [] && reverse ls <= rs = let ls' = succ ls in ls' ++ reverse (take (length ls) ls')
	| m == [] && reverse ls > rs = ls ++ reverse ls
	| reverse ls > rs = ls ++ m ++ reverse ls
	| length (succ m) == 1 = ls ++ succ m ++ reverse ls
	| otherwise = let ls' = succ (ls ++ m) in ls' ++ reverse (take (length ls) ls')
	where (ls, m, rs) = divide n

succ :: String -> String
succ = reverse . f False . reverse where
	f True [] = "1"
	f False [] = []
	f carry (x:xs) = if x < '9' then chr (ord x + 1) : xs else '0' : f True xs

main = do
	n <- read `fmap` getLine :: IO Int
	replicateM_ n $ do
		x <- getLine
		putStrLn $ np x
