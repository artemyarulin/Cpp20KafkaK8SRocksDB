#include <cstdio>
#include <string>

#include "rocksdb/db.h"
#include "rocksdb/options.h"

export module storage;

export class Storage {
public:
  Storage(std::string path, std::function<void(std::string)> log) {
    this->log = log;
    log("Openning DB at: " + path);
    rocksdb::Options options;
    options.create_if_missing = true;
    auto s = rocksdb::DB::Open(options, path, &db);
    assert(s.ok());
  }

  void Write(std::string key, std::string val) {
    auto s = db->Put(rocksdb::WriteOptions(), key, val);
    assert(s.ok());
  }

  std::string Read(std::string key) {
    std::string val;
    auto s = db->Get(rocksdb::ReadOptions(), key, &val);
    assert(s.ok());
    return val;
  }

  void Close() {
    log("Closing database");
    auto s = db->Close();
    assert(s.ok());
    delete db;
  }

private:
  std::function<void(std::string)> log;
  rocksdb::DB *db;
};
