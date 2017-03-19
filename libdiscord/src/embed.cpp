#include "embed.h"
#include "connection_state.h"

namespace discord
{
  embed_footer::embed_footer(connection_state* owner, rapidjson::Value& data)
  {
    set_from_json(m_text, "text", data);
    set_from_json(m_icon_url, "icon_url", data);
    set_from_json(m_proxy_icon_url, "proxy_icon_url", data);
  }

  embed_footer::embed_footer(std::string text, std::string icon_url, std::string proxy_icon_url)
    : m_text(text), m_icon_url(icon_url), m_proxy_icon_url(proxy_icon_url)
  {
  }

  std::string embed_footer::content() const
  {
    return m_text;
  }

  std::string embed_footer::icon_url() const
  {
    return m_icon_url;
  }

  std::string embed_footer::proxy_icon_url() const
  {
    return m_proxy_icon_url;
  }

  embed_image::embed_image(connection_state* owner, rapidjson::Value& data)
  {
    set_from_json(m_url, "url", data);
    set_from_json(m_proxy_url, "proxy_url", data);
    set_from_json(m_height, "height", data);
    set_from_json(m_width, "width", data);
  }

  embed_image::embed_image(std::string url, uint32_t width, uint32_t height, std::string proxy_url)
    : m_url(url), m_proxy_url(proxy_url), m_height(height), m_width(width)
  {
  }

  std::string embed_image::url() const
  {
    return m_url;
  }

  std::string embed_image::proxy_url() const
  {
    return m_proxy_url;
  }

  uint32_t embed_image::width() const
  {
    return m_width;
  }

  uint32_t embed_image::height() const
  {
    return m_height;
  }

  embed_video::embed_video(connection_state* owner, rapidjson::Value& data)
  {
    set_from_json(m_url, "url", data);
    set_from_json(m_height, "height", data);
    set_from_json(m_width, "width", data);
  }

  embed_video::embed_video(std::string url, uint32_t width, uint32_t height)
    : m_url(url), m_height(height), m_width(width)
  {
  }

  std::string embed_video::url() const
  {
    return m_url;
  }

  uint32_t embed_video::width() const
  {
    return m_width;
  }

  uint32_t embed_video::height() const
  {
    return m_height;
  }

  embed_provider::embed_provider(connection_state* owner, rapidjson::Value& data)
  {
    set_from_json(m_name, "name", data);
    set_from_json(m_url, "url", data);
  }

  embed_provider::embed_provider(std::string name, std::string url)
    : m_name(name), m_url(url)
  {
  }

  std::string embed_provider::name() const
  {
    return m_name;
  }

  std::string embed_provider::url() const
  {
    return m_url;
  }

  embed_author::embed_author(connection_state* owner, rapidjson::Value& data)
  {
    set_from_json(m_name, "name", data);
    set_from_json(m_url, "url", data);
    set_from_json(m_icon_url, "icon_url", data);
    set_from_json(m_proxy_icon_url, "proxy_icon_url", data);
  }

  embed_author::embed_author(std::string name, std::string url, std::string icon_url, std::string proxy_icon_url)
    : m_name(name), m_url(url), m_icon_url(icon_url), m_proxy_icon_url(proxy_icon_url)
  {
  }

  std::string embed_author::name() const
  {
    return m_name;
  }

  std::string embed_author::url() const
  {
    return m_url;
  }

  std::string embed_author::icon_url() const
  {
    return m_icon_url;
  }

  std::string embed_author::proxy_icon_url() const
  {
    return m_proxy_icon_url;
  }

  embed_field::embed_field()
  {
    m_inline = false;
  }

  embed_field::embed_field(connection_state* owner, rapidjson::Value& data)
  {
    set_from_json(m_name, "name", data);
    set_from_json(m_value, "value", data);
    set_from_json(m_inline, "inline", data);
  }

  embed_field::embed_field(std::string name, std::string value, bool is_inline)
    : m_name(name), m_value(value), m_inline(is_inline)
  {
  }

  std::string embed_field::name() const
  {
    return m_name;
  }

  std::string embed_field::content() const
  {
    return m_value;
  }

  bool embed_field::is_inline() const
  {
    return m_inline;
  }

  embed::embed()
  {
    m_color = 0;
  }

  embed::embed(connection_state* owner, rapidjson::Value& data)
  {
    set_from_json(m_title, "title", data);
    set_from_json(m_type, "type", data);
    set_from_json(m_description, "description", data);
    set_from_json(m_url, "url", data);
    set_from_json(m_timestamp, "timestamp", data);
    set_from_json(m_color, "color", data);

    auto found = data.FindMember("footer");
    if (found != data.MemberEnd() && !found->value.IsNull())
    {
      m_footer = embed_footer(owner, data);
    }

    found = data.FindMember("image");
    if (found != data.MemberEnd() && !found->value.IsNull())
    {
      m_image = embed_image(owner, data);
    }

    found = data.FindMember("thumbnail");
    if (found != data.MemberEnd() && !found->value.IsNull())
    {
      m_thumbnail = embed_thumbnail(owner, data);
    }

    found = data.FindMember("video");
    if (found != data.MemberEnd() && !found->value.IsNull())
    {
      m_video = embed_video(owner, data);
    }

    found = data.FindMember("provider");
    if (found != data.MemberEnd() && !found->value.IsNull())
    {
      m_provider = embed_provider(owner, data);
    }

    found = data.FindMember("author");
    if (found != data.MemberEnd() && !found->value.IsNull())
    {
      m_author = embed_author(owner, data);
    }

    found = data.FindMember("fields");
    if (found != data.MemberEnd() && !found->value.IsNull())
    {
      for (auto& field : found->value.GetArray())
      {
        m_fields.push_back(embed_field(owner, field));
      }
    }
  }

  void embed::set_title(std::string title)
  {
    m_title = title;
  }

  void embed::set_description(std::string description)
  {
    m_description = description;
  }

  void embed::set_url(std::string url)
  {
    m_url = url;
  }

  void embed::set_footer(std::string text, std::string icon_url, std::string proxy_icon_url)
  {
    m_footer = embed_footer(text, icon_url, proxy_icon_url);
  }

  void embed::set_image(std::string url)
  {
    m_image = embed_image(url);
  }

  void embed::set_thumbnail(std::string url)
  {
    m_thumbnail = embed_thumbnail(url);
  }

  void embed::set_video(std::string url)
  {
    m_video = embed_video(url);
  }

  void embed::set_author(std::string name, std::string url, std::string icon_url)
  {
    m_author = embed_author(name, url, icon_url);
  }

  void embed::add_field(std::string name, std::string value, bool is_inline)
  {
    m_fields.push_back(embed_field(name, value, is_inline));
  }

  std::string embed::title() const
  {
    return m_title;
  }

  std::string embed::type() const
  {
    return m_type;
  }

  std::string embed::description() const
  {
    return m_description;
  }

  std::string embed::url() const
  {
    return m_url;
  }

  std::string embed::timestamp() const
  {
    return m_timestamp;
  }

  uint32_t embed::color() const
  {
    return m_color;
  }

  embed_footer& embed::footer()
  {
    return m_footer;
  }

  embed_image& embed::image()
  {
    return m_image;
  }

  embed_thumbnail& embed::thumbnail()
  {
    return m_thumbnail;
  }

  embed_video& embed::video()
  {
    return m_video;
  }

  embed_provider& embed::provider()
  {
    return m_provider;
  }

  embed_author& embed::author()
  {
    return m_author;
  }

  std::vector<embed_field>& embed::fields()
  {
    return m_fields;
  }

  bool embed::empty() const
  {
    return  m_title.empty() && m_description.empty() &&
            m_footer.empty() && m_image.empty() &&
            m_thumbnail.empty() && m_video.empty() &&
            m_provider.empty() && m_author.empty() && m_fields.size() == 0;
  }
}