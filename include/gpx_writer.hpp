#ifndef GPX_WRITER_HPP
#define GPX_WRITER_HPP

#include "types.hpp"
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/program_options.hpp>
#include <map>
#include <string>
#include <vector>

/**
 * writes GPS traces to a GPX 1.0 file, in the same format as the trackpoints
 * API: one <trk> per trace and one <trkseg> per trackid. identifiable traces
 * also have name, description and URL.
 */
class gpx_writer : private boost::noncopyable {
public:
  typedef std::map<int64_t, std::string> user_map_t;

  gpx_writer(const std::string &, const boost::program_options::variables_map &, const user_map_t &,
             const boost::posix_time::ptime &max_time);
  ~gpx_writer();

  // write one trace. the tracks must be ordered by (trackid, segment).
  void trace(const gpx_file &, const std::vector<gpx_track> &);

  // close the document and the output stream.
  void finish();

  struct pimpl;

private:
  boost::scoped_ptr<pimpl> m_impl;
  const user_map_t &m_users;
};

#endif /* GPX_WRITER_HPP */
