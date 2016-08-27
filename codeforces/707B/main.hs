import Data.Maybe
import Control.Monad
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8
import qualified Data.Map.Strict as Map
import qualified Data.IntSet as Set

-- ID:	707B (Bakery)
-- URL:	http://codeforces.com/problem/707/B

getInt = read `fmap` getLine :: IO Int
getInts = (map (fst . fromJust . BS8.readInt) . BS8.words) `fmap` BS.getLine :: IO [Int]

type Links = Map.Map Int [(Int,Int)] -- (dest, weight)

main = do
	[n,m,k] <- getInts
	edges <- replicateM m getInts	-- m numbers of [u,v,l]
	if k == 0 || k == n
	then print (-1)
	else do
		storages <- getInts				-- length: k
		let links = foldl mkLink Map.empty edges :: Links
		let storageCities = Set.fromList storages
		let inf = 10^9 + 7
		-- for each stroage, find the nearest empty city
		let soln = foldl findNearest inf storages where
			findNearest minCost storage = if costs == [] then minCost else min (minimum costs) minCost where
				costs = (map snd . filter notStorage) (neighbors storage)
				neighbors storage = if storage `Map.member` links then links Map.! storage else []
				notStorage (city,len) = city `Set.notMember` storageCities
		if soln == inf
		then print (-1)
		else print soln

mkLink links [u,v,l] = links2 where
	links1 = Map.insertWith (++) u [(v,l)] links
	links2 = Map.insertWith (++) v [(u,l)] links1
