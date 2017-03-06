-- Codeforces Round #403 (Div. 2)
-- A. Andryusha and Socks
-- http://codeforces.com/contest/782/problem/A

import Control.Monad
import Data.Maybe
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8
import qualified Data.Set as Set

getInt = read `fmap` getLine :: IO Int
getInts = (map parseInt . BS8.words) `fmap` BS.getLine :: IO [Int]
parseInt = fst . fromJust . BS8.readInt

type State = (Set.Set Int, Int, Int)

main = do
	n <- getInt
	socks <- getInts
	let (_, _, answer) = foldl pick (Set.empty, 0, 0) socks
	print answer

pick (table, curr, answer) sock
	| sock `Set.member` table = (table, curr - 1, answer)
	| otherwise = (sock `Set.insert` table, curr + 1, max answer (curr + 1))
