-- Codeforces Round #379 (Div. 2)
-- http://codeforces.com/contest/734

-- ID: 734F (Anton and School)

import Control.Monad
import Data.Int
import Data.Bits
import Data.Array.IArray
import Data.Array.Unboxed
import Data.Maybe
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8

getInt = read `fmap` getLine :: IO Int
getInts = (map parseInt . BS8.words) `fmap` BS.getLine :: IO [Int]
getIntArray n = listArray (1,n) `fmap` getInts :: IO (UArray Int Int)
parseInt = fst . fromJust . BS8.readInt

main = do
	n <- getInt
	bs <- getIntArray n
	cs <- getIntArray n
	let ds = listArray (1,n) [fromIntegral (bs ! i) + fromIntegral (cs ! i) | i <- [1..n]] :: UArray Int Int64
	let as = getOriginal ds n
	let asBits = bitOccurences (elems as)
	let bsTable = array ((1,0),(n,maxBits)) [((i,j), if (as ! i .&. bit j) == 0 then 0 else asBits ! j) | i <- [1..n], j <- [0..maxBits]] :: UArray (Int,Int) Int
	let csTable = array ((1,0),(n,maxBits)) [((i,j), if (as ! i .&. bit j) == 0 then asBits ! j else n) | i <- [1..n], j <- [0..maxBits]] :: UArray (Int,Int) Int
	let bs' = accumArray (+) 0 (1,n) [(i, (bsTable ! (i,j)) * (bit j)) | i <- [1..n], j <- [0..maxBits]]
	let cs' = accumArray (+) 0 (1,n) [(i, (csTable ! (i,j)) * (bit j)) | i <- [1..n], j <- [0..maxBits]]
	if bs' /= bs || cs' /= cs
	then print (-1)
	else forM_ (elems as) $ \a -> putStr (show a) >> putChar ' '

getOriginal :: UArray Int Int64 -> Int -> UArray Int Int
getOriginal ds n = listArray (1,n) [fromIntegral ((ds ! i - sumA) `div` n') :: Int | i <- [1..n]] where
	sumA = (sum $ elems ds) `div` (2 * n') :: Int64
	n' = fromIntegral n :: Int64

maxBits = 31 :: Int
bitOccurences as = accumArray (+) (0::Int) (0,maxBits) (concatMap toBits as) :: UArray Int Int
toBits x = map (\j -> (j,1)) $ filter (\j -> (x .&. bit j) >= 1) [0..maxBits]
