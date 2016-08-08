import Data.List
import Control.Monad
import qualified Data.ByteString.Char8 as BS

-- ID:	PDNA
-- URL:	https://algospot.com/judge/problem/read/PDNA

getInt = read `fmap` getLine :: IO Int

main = do
    n <- getInt
    replicateM_ n solve

-- each dna is a bytestring
palindrome2 :: BS.ByteString -> Bool
palindrome2 xs = xs == BS.reverse xs

compareDNA (x,px) (y,py)
	| not px && not py = EQ
	| px && py = compare x y
	| px && not py = LT
	| not px && py = GT

least (x:xs) = f x xs where
	f x [] = fst x
	f x (y:ys) = case compareDNA x y of
		LT -> f x ys
		_ -> f y ys

solve = do
	pieces <- (tail . words) `fmap` getLine :: IO [String]
	let p = map BS.pack pieces
	putStrLn $ BS.unpack $ least $ map (\x -> (x, palindrome2 x)) $ map BS.concat $ permutations p
