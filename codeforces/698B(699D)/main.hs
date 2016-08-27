import Data.List
import Data.Array
import Data.Maybe
import Control.Monad
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8
import qualified Data.IntSet as Set

-- ID:	699D (Fix a Tree)
-- URL:	http://codeforces.com/contest/699/problem/D

-- This is not a valid code!

getInt = read `fmap` getLine :: IO Int
getInts = (map (fst . fromJust . BS8.readInt) . BS8.words) `fmap` BS.getLine :: IO [Int]

main = do
	n <- getInt
	ns <- getInts
	let vs = zip [1..n] ns
	let roots@(r0:_) = [v | (v,p) <- vs, v == p]
	let rootSet = foldl (\set x -> Set.insert x set) Set.empty roots
	let revised = [if Set.member v rootSet then r0 else p | (v,p) <- vs]
	print (length roots - 1)
	putStrLn $ concat (map (\x -> show x ++ " ") revised)
