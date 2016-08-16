import Data.Maybe
import Data.List
import Control.Monad
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8

-- ID:	The Sums of Powers
-- URL:	https://www.hackerrank.com/challenges/functional-programming-the-sums-of-powers

getInt = read `fmap` getLine :: IO Int
getInts = (map (fst . fromJust . BS8.readInt) . BS8.words) `fmap` BS.getLine :: IO [Int]

sqrt_int = floor . sqrt . fromIntegral
nth_root x n = exp (1/n * log x)

main = do
	x <- getInt
	n <- getInt
	print $ length $ solve x n

-- solutions for (x,n)
solve :: Int -> Int -> [([Int],Int)]
solve x n  = filter valid (subsets powers x) where
	valid ls = snd ls == x
	-- precision error; +1 needed
	maxPower = floor (nth_root (fromIntegral x) (fromIntegral n)) + 1 :: Int
	powers = reverse [x^n | x <- [1..maxPower]] :: [Int]

subsets powers goal = f powers where
	f [] = [([],0)]
	f (x:xs) = xss ++ filter promising (map (append x) xss) where
		xss = f xs
	append x (ls,acc) = (x:ls, x+acc)
	promising (ls,acc) = acc <= goal
