-- ID:  JUMPGAME (외발뛰기)
-- URL: https://algospot.com/judge/problem/read/JUMPGAME

import Control.Monad
import Data.Array
import Data.Array.MArray
import Data.Array.ST

-- for fast input (getInts)
-- running time: 328ms -> 40ms (C++ version takes 28ms)
import Data.Maybe
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8

getInt = read `fmap` getLine :: IO Int
--getInts = (map read . words) `fmap` getLine :: IO [Int]
getInts = (map (fst . fromJust . BS8.readInt) . BS8.words) `fmap` BS.getLine :: IO [Int]

main = do
	c <- getInt
	replicateM_ c solve

solve = do
	n <- getInt
	rows <- replicateM n getInts
	let es = concat [divRow row n | row <- (zip [1..n] rows)]
	let board = array ((1,1),(n,n)) es
	if possibleJump board (1,1) (n,n)
	then putStrLn "YES"
	else putStrLn "NO"

divRow (row, xs) n = [((row,col),x) | (col,x) <- (zip [1..n] xs)]

possibleJump :: Array (Int,Int) Int -> (Int,Int) -> (Int,Int) -> Bool
possibleJump board (y1,x1) (y2,x2) = jump ! (y2,x2) where
	jump = runSTArray $ do
		ary <- newArray ((y1,x1),(y2+10,x2+10)) False
		writeArray ary (y1,x1) True
		forM [y1..y2] $ \i -> do
			forM [x1..x2] $ \j -> do
				valid <- readArray ary (i,j)
				when valid $ do
					let power = board ! (i,j)
					writeArray ary (i+power,j) True
					writeArray ary (i,j+power) True
		return ary
